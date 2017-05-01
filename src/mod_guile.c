#include "guile_apache.h"

#include <libguile.h>

module AP_MODULE_DECLARE_DATA guile_module;

size_t
ap_port_write(SCM port, SCM src, size_t start, size_t count)
{
  request_rec *request = (request_rec *)SCM_STREAM (port);

  return ap_rwrite(SCM_BYTEVECTOR_CONTENTS (src) + start, count, request);
}


typedef struct guile_server_config{
  const char *path;
  const char *file;
} guile_server_config_t;


void *
guile_execute_script(request_rec *request)
{
  const char *script = NULL;
  const char *name = NULL;
  SCM source;
  int exists = 0;
  int status = 0;

  return OK;
}

void *
guile_init(void *request_data)
{
  guile_server_config_t *server_config = NULL;
  request_rec *request = NULL;
  scm_t_port_type *apache_port_type = 0;
  SCM request_rec_pointer = NULL;
  SCM status = NULL;
  SCM apache_port = NULL;

  request = (request_rec *)request_data;

  apache_port_type = scm_make_port_type("apache-port", NULL, ap_port_write);

  apache_port = scm_c_make_port(apache_port_type, SCM_WRTNG, (scm_t_bits)request);

  request_rec_pointer = scm_from_pointer(request, NULL);

  server_config = (guile_server_config_t *)ap_get_module_config(request->server->module_config, &guile_module);

  scm_c_define("<apache-port>", apache_port);
  ap_set_content_type(request, "text/plain");
  ap_send_http_header(request);
  status = scm_c_primitive_load(server_config->file);

  return guile_execute_script(request);

}


static void
guile_build_env(request_rec *r)
{
  const char *script_name = NULL;
  const char *path_info = NULL;

  conn_rec *conn = r->connection;

  ap_add_cgi_vars(r);
  ap_add_common_vars(r);
}

static int
guile_hook_handler(request_rec *r)
{
  int status;
  apr_off_t limit = 0;

  guile_build_env(r);

  scm_with_guile(guile_init, r);

  return OK;
}


static const char *
guile_add_script_alias(cmd_parms *cmd, void *mconfig, const char *path, const char *file)
{

  guile_server_config_t *server_config = mconfig;
  server_config = ap_get_module_config(cmd->server->module_config, &guile_module);

  server_config->path = apr_pstrdup(cmd->pool, path);
  server_config->file = apr_pstrdup(cmd->pool, file);

  return NULL;
}

static int
guile_hook_init(apr_pool_t *pconf, apr_pool_t *ptemp,
		apr_pool_t *plog, server_rec *server)
{
  ap_add_version_component (pconf, "mod_guile/");
  return OK;
}

static void
guile_register_hooks(apr_pool_t *p)
{
  static const char * const p1[] = {"mod_alias.c", NULL};
  static const char * const n1[] = {"mod_userdir.c",
				    "mod_vhost_alias.c", NULL};
  static const char * const n2[] = {"core.c", NULL};

  ap_hook_post_config(guile_hook_init, NULL, NULL, APR_HOOK_MIDDLE);
  //  ap_hook_child_init(guile_hook_child_init, NULL, NULL, APR_HOOK_MIDDLE);
  ap_hook_handler(guile_hook_handler, NULL, NULL, APR_HOOK_LAST);
}

static void *
guile_create_server_config(apr_pool_t *pool, server_rec *server)
{
  guile_server_config_t *config = NULL;

  config = (guile_server_config_t *)apr_pcalloc(pool, sizeof(guile_server_config_t));

  return config;
}

static void *
guile_merge_server_config(apr_pool_t *pool, void *base_config, void *new_config)
{

  guile_server_config_t *config = NULL;

  config = (guile_server_config_t *)apr_pcalloc(pool, sizeof(guile_server_config_t));

  return config;
}

static const command_rec guile_commands[] =
  {
    AP_INIT_TAKE2("GuileScriptAlias", guile_add_script_alias,
		  NULL, RSRC_CONF, "Map location to target guile script file."),
    { NULL }
  };

module AP_MODULE_DECLARE_DATA guile_module =
  {
    STANDARD20_MODULE_STUFF,
    NULL,//guile_create_dir_config,
    NULL,//guile_merge_dir_config,
    guile_create_server_config,
    NULL,//guile_merge_server_config,
    guile_commands,
    guile_register_hooks
  };

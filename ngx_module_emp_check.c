#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

static char* ngx_emp_check_readconf(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
static void* ngx_emp_check_create_loc_conf(ngx_conf_t *cf);
static char* ngx_emp_check_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child);

typedef struct {
    ngx_str_t ecdata;
    ngx_flag_t           enable;
} ngx_emp_check_loc_conf_t;

static ngx_command_t  ngx_emp_check_commands[] = {
    { ngx_string("emp_check"),
      NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
      ngx_emp_check_readconf,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_emp_check_loc_conf_t, ecdata),
      NULL },
      ngx_null_command
};


static ngx_http_module_t  ngx_emp_check_module_ctx = {
    NULL,                          /* preconfiguration */
    NULL,           /* postconfiguration */

    NULL,                          /* create main configuration */
    NULL,                          /* init main configuration */

    NULL,                          /* create server configuration */
    NULL,                          /* merge server configuration */

    ngx_emp_check_create_loc_conf,  /* create location configuration */
    ngx_emp_check_merge_loc_conf /* merge location configuration */
};


ngx_module_t  ngx_module_emp_check = {
    NGX_MODULE_V1,
    &ngx_emp_check_module_ctx, /* module context */
    ngx_emp_check_commands,   /* module directives */
    NGX_HTTP_MODULE,               /* module type */
    NULL,                          /* init master */
    NULL,                          /* init module */
    NULL,                          /* init process */
    NULL,                          /* init thread */
    NULL,                          /* exit thread */
    NULL,                          /* exit process */
    NULL,                          /* exit master */
    NGX_MODULE_V1_PADDING
};


static ngx_int_t
ngx_emp_check_handler(ngx_http_request_t *r)
{
    printf("called:ngx_emp_check_handler\n");
    return NGX_OK;
}
static char *
ngx_emp_check_readconf(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    printf("called:ngx_emp_check_readconf\n");
    ngx_http_core_loc_conf_t  *clcf;

    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    clcf->handler = ngx_emp_check_handler;
    ngx_conf_set_str_slot(cf,cmd,conf);
    return NGX_CONF_OK;
}


static void *
ngx_emp_check_create_loc_conf(ngx_conf_t *cf)
{
    printf("called:ngx_emp_check_create_loc_conf\n");
    ngx_emp_check_loc_conf_t  *conf;

    conf = ngx_pcalloc(cf->pool, sizeof(ngx_emp_check_loc_conf_t));
    if (conf == NULL) {
        return NGX_CONF_ERROR;
    }

    conf->ecdata.len=0;
    conf->ecdata.data=NULL;
    conf->enable = NGX_CONF_UNSET;
    return conf;
}
static char *
ngx_emp_check_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child)
{
    printf("called:ngx_emp_check_merge_loc_conf\n");
    ngx_emp_check_loc_conf_t *prev = parent;
    ngx_emp_check_loc_conf_t *conf = child;

    ngx_conf_merge_str_value(conf->ecdata, prev->ecdata, 10);
    ngx_conf_merge_value(conf->enable, prev->enable, 0);
/**
    if(conf->enable)
        ngx_echo_init(conf);
        */
    return NGX_CONF_OK;
    return NGX_CONF_OK;
}


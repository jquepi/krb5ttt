#include <assert.h>

#include "gssapi_err_generic.h"
#include "gssapi_err_krb5.h"
#include "gssapiP_krb5.h"

#include "gss_libinit.h"

static	int		initialized = 0;

/*
 * Initialize the GSSAPI library.
 */

OM_uint32 gssint_initialize_library (void)
{
	
	if (!initialized) {
#if !TARGET_OS_MAC || USE_HARDCODED_FALLBACK_ERROR_TABLES
	    add_error_table(&et_k5g_error_table);
	    add_error_table(&et_ggss_error_table);
#endif

		initialized = 1;
	}
	
	return 0;
}

/*
 * Clean up the Kerberos v5 lirbary state
 */

void gssint_cleanup_library (void)
{
	OM_uint32 min_stat;

	assert (initialized);
	
	(void) kg_release_defcred (&min_stat);
	
#if !TARGET_OS_MAC || USE_HARDCODED_FALLBACK_ERROR_TABLES
	remove_error_table(&et_k5g_error_table);
	remove_error_table(&et_ggss_error_table);
#endif
	
	initialized = 0;
}

/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "minifyjpeg.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

int
_minifyjpeg_proc_1 (minifyjpeg_input  *argp, void *result, struct svc_req *rqstp)
{
	return (minifyjpeg_proc_1_svc(*argp, result, rqstp));
}

static void
minifyjpeg_prog_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		minifyjpeg_input minifyjpeg_proc_1_arg;
	} argument;
	union {
		minifyjpeg_output minifyjpeg_proc_1_res;
	} result;
	bool_t retval;
	xdrproc_t _xdr_argument, _xdr_result;
	bool_t (*local)(char *, void *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case MINIFYJPEG_PROC:
		_xdr_argument = (xdrproc_t) xdr_minifyjpeg_input;
		_xdr_result = (xdrproc_t) xdr_minifyjpeg_output;
		local = (bool_t (*) (char *, void *,  struct svc_req *))_minifyjpeg_proc_1;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	retval = (bool_t) (*local)((char *)&argument, (void *)&result, rqstp);
	if (retval > 0 && !svc_sendreply(transp, (xdrproc_t) _xdr_result, (char *)&result)) {
		printf("Check\n");
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	if (!minifyjpeg_prog_1_freeresult (transp, _xdr_result, (caddr_t) &result))
		fprintf (stderr, "%s", "unable to free results");

	return;
}

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (MINIFYJPEG_PROG, MINIFYJPEG_VERS);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, MINIFYJPEG_PROG, MINIFYJPEG_VERS, minifyjpeg_prog_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (MINIFYJPEG_PROG, MINIFYJPEG_VERS, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, MINIFYJPEG_PROG, MINIFYJPEG_VERS, minifyjpeg_prog_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (MINIFYJPEG_PROG, MINIFYJPEG_VERS, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}

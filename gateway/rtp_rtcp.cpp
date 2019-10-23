#include "rtp_rtcp.h"
#include <stdio.h>
bool is_dtls(char *buf) 
{
    return ((*buf >= 20) && (*buf <= 64));
}
bool is_rtp(char *buf) 
{
    rtp_header *header = (rtp_header *)buf;
    return ((header->type < 64) || (header->type >= 96));
}

bool is_rtcp(char *buf) 
{
    rtp_header *header = (rtp_header *)buf;
    return ((header->type >= 64) && (header->type < 96));
}





char *janus_rtp_payload(char *buf, int len, int *plen) {
	if (!buf || len < 12)
		return NULL;
	rtp_header *rtp = (rtp_header *)buf;
	if (rtp->version != 2) {
		return NULL;
	}
	int hlen = 12;
	if (rtp->csrccount)	/* Skip CSRC if needed */
	{
		hlen += rtp->csrccount * 4;
		printf("csrccount4 \n");
	}

	if (rtp->extension) {
		printf("rtp_extension \n");
		janus_rtp_header_extension *ext = (janus_rtp_header_extension*)(buf + hlen);
		int extlen = ntohs(ext->length) * 4;
		hlen += 4;
		if (len > (hlen + extlen)) {
			hlen += extlen;
			printf("extlen \n");
		}
	}
	if (len - hlen <= 0) {
		return NULL;
	}
	if (plen)
		*plen = len - hlen;
	printf("len:%d,plen:%d,HLEN:%d \n", len,*plen,hlen);
	return buf + hlen;
}



//HELLO WORLD MONGOOSE WEB SERVER

#include "mongoose.h"


// to convert uint_32 ip to 4 numbers we can use union ip_t ip = {.in = 12456432} then it computes representation out and you can read it like ip.out[0]

union ip_t { // ip conversion into 4 numbers with union
	uint32_t in; 
	uint8_t out[4];
};

//EVENT HANDLER
static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
	
	//neeeded for https
	if (ev == MG_EV_ACCEPT) {
		struct mg_tls_opts opts = {
		  .cert = "cert.pem",    // Certificate file
		  .certkey = "key.pem",  // Private key file
		};
		mg_tls_init(c, &opts);
	}
  
  if (ev == MG_EV_HTTP_MSG) { // HTTP request/response 
    
	union ip_t ip = {.in = c->rem.ip};
	char timebuf[9]; time_t now = time(NULL);strftime(timebuf, 9, "%H:%M:%S", localtime(&now));
	printf("%s : con ip %d.%d.%d.%d ",timebuf,ip.out[0],ip.out[1],ip.out[2],ip.out[3]); // show ip and timestamp
	
	struct mg_http_message *hm = (struct mg_http_message *) ev_data;
	if (mg_http_match_uri(hm, "/time")) // will return special string
	{
		char timebuf[9]; time_t now = time(NULL);strftime(timebuf, 9, "%H:%M:%S", localtime(&now));
		char rep_msg[128];	sprintf(rep_msg,"current server time is %s.", timebuf);
		mg_http_reply(c, 200, "", rep_msg,"status", 1); 
	}
	
	else {                                                // For all other URIs,
      struct mg_http_serve_opts opts = {.root_dir = "FILES"};   // Serve files
      mg_http_serve_dir(c, hm, &opts);                      // From root_dir
    }
  }
}

int main(int argc, char *argv[]) {
  struct mg_mgr mgr;
  mg_mgr_init(&mgr);                                      // Init manager
  printf("starting http listener\n\n");
  mg_http_listen(&mgr, "http://0.0.0.0:443", fn, &mgr);  // Setup listener
  for (;;) mg_mgr_poll(&mgr, 1000);                       // Event loop
  mg_mgr_free(&mgr);                                      // Cleanup
  return 0;
}
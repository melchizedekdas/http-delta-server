# http-delta-server
server to implement delta response to improve caching

to compile run the following in src:
"gcc -o httpserver server.c tcp_socket.c http.c http_response.c resource.c -I ."

keep a version of web-inf folder in the parent directory of src before testing. The name of the folder should be "web-inf".

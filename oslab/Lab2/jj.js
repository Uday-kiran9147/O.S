//write a program to create a server on port 3000
//and display the message "Hello World" on the browser
//when the user enters the url http://localhost:3000
const server = require('http'); 
server.createServer(function(req,res){
    res.writeHead(200,{'Content-Type':'text/plain'});
    res.end('Hello Worldadfasdf');
}).listen(3000);

/*  
  Very simple TCP client to test host/server capabilities 
  of the ESP8266 wifi module.
*/

var net = require('net'); // Load up the required library for TCP stuff

// Create a new TCP socket 
var client = new net.Socket(); 
client.connect(8080, '192.168.1.189', function() { // Connect to the chip
  console.log('Connected');
  client.write('Hello, server! Love, Client.\r\n'); // Send some text
  client.write('This is really really cool!\r\n') // Send some more text
});
 
// When data is recieved, call "data()"
client.on('data', data);

// When connection is closed, let us know
client.on('close', function() {
  console.log('Connection closed');
});

// Callback upon receiving data from the server
function data(data) {
  console.log('Received: ' + data);
  client.destroy(); // kill client after server's response
}
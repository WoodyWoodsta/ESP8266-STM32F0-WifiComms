/*
  Very simple TCP client to test host/server capabilities
  of the ESP8266 wifi module.
*/

var net = require('net'); // Load up the required library for TCP stuff

// Create a new TCP socket
var client = new net.Socket();
client.connect(3000, '192.168.137.243', function() { // Connect to the chip
  console.log('Connected');

  client.write('This is a very long string to test out the wifi to it\'s fullllllll capacity!!!\r\n');
  // console.log('LEDs Off command sent');
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
  // client.destroy(); // kill client after server's response
}

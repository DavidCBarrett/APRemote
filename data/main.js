
var url = `ws://${window.location.hostname}/ws`;
var websocket;
// request data updates every 1000 millisecond
setInterval(requestData, 1000);

function requestData() {

var xhr = new XMLHttpRequest();

  xhr.open('GET', 'getData');

  xhr.onload = function() {
    if (xhr.status === 200) {
      if (xhr.responseText) { // if the returned data is not null, update the values
        var data = JSON.parse(xhr.responseText);

        document.getElementById("CTS").innerText = data.cts;

        document.getElementById("LED0").innerHTML = "<div class=\"" + data.led0 + "\"></div>";
        document.getElementById("LED1").innerHTML = "<div class=\"" + data.led1 + "\"></div>";
        document.getElementById("LED2").innerHTML = "<div class=\"" + data.led2 + "\"></div>";
        document.getElementById("LED3").innerHTML = "<div class=\"" + data.led3 + "\"></div>";

        document.getElementById("HDG").innerText = data.hdg;
        document.getElementById("RSA").innerText = data.rsa;  
        document.getElementById("COG").innerText = data.cog;
        document.getElementById("SOG").innerText = data.sog;
        document.getElementById("AWA").innerText = data.awa;
        document.getElementById("AWS").innerText = data.aws;
        document.getElementById("DPT").innerText = data.dpt;
        document.getElementById("STW").innerText = data.stw;
        document.getElementById("XTE").innerText = data.xte;
        document.getElementById("BTW").innerText = data.btw;
        document.getElementById("DTW").innerText = data.dtw;
        document.getElementById("VLW").innerText = data.vlw;
        
        document.getElementById("left").innerHTML = data.left;
        document.getElementById("right").innerHTML = data.right;
        document.getElementById("hdgInfo").innerHTML = data.hdgInfo;
        document.getElementById("alarm").innerText = data.alm;
      } 
    }
  };
  xhr.send();
}

document.addEventListener("DOMContentLoaded", function() {
websocket = new ReconnectingWebSocket(url);
websocket.debug = true;
websocket.timeoutInterval = 1000;

  websocket.onopen = () => {
      console.log("Websocket connection established")
  }

  websocket.onclose = () => {
      console.log("Websocket connection closed")
  }

  websocket.onerror = error => {
      console.log(error)
  }
})

// Called whenever the HTML button is pressed
function onPress(msg) {
  console.log(`Received a msg to send to ESP32 from ${msg.origin}`);
  console.log(msg);
  websocket.send(msg);
}
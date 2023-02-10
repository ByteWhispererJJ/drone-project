<input type="range" min="0" max="150" value="50" class="slider" id="myRange">

<script>
  let socket = new WebSocket("ws://192.168.178.177:65");
  setTimeout(function() {

    socket.send('register;controller;jer');
    //socket.send('drone_command;drone1;setrotorspeed;0;150');
    socket.send('drone_command;drone1;setrotorspeed;0;50');
  }, 1000);

  var myRange = document.getElementById("myRange");
  myRange.oninput = function(event)
  {
    var sendval = myRange.value;
    socket.send('drone_command;drone1;setrotorspeed;0;'+sendval+"");
  };


</script>

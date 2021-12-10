const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
    <link rel="stylesheet" href="../style/style.css">
</head>
<style>
body{
    background: #76BED0;
}
.card{
    max-width: 400px;
     min-height: 250px;
     background: #F33B16;
     padding: 30px;
     box-sizing: border-box;
     color: #FFF;
     margin-right:auto;
     margin-left: auto;
     box-shadow: 0px 2px 18px -4px rgba(0,0,0,0.75);
}
h1{text-align: center;}
button{
    margin-left: auto;
    margin-right: auto;
}
</style>
<body>

<div class="card">
  <h1>Teplota:</h1><br>
  <h1><span id="ADCValue">0</span></h1><br>
  <button>EXPORT</button>
</div>
<script>

setInterval(function() {
  // Call a function repetatively with 2 Second interval
  getData();
}, 2000); //2000mSeconds update rate

function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("ADCValue").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "readADC", true);
  xhttp.send();
}
</script>
</body>
</html>
)=====";
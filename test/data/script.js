var values = [];
var values2 = [];
var timeStamp = [];
function showGraph()
{

    var ctx = document.getElementById("Chart").getContext('2d');
    var Chart2 = new Chart(ctx, {
        type: 'line',
        data: {
            labels: timeStamp,	//Bottom Labeling
            datasets: [{
                label: "Teplota",
                fill: false,	//Try with true
                backgroundColor: 'rgba( 243, 156, 18 , 1)', //Dot marker color
                borderColor: 'rgba( 243, 156, 18 , 1)',	//Graph Line Color
                data: values,
            },{
                label: "Vlhkost",
                fill: false,	//Try with true
                backgroundColor: 'rgba(25, 152, 231, 1)', //Dot marker color
                borderColor: 'rgba(25, 152, 231, 1)',	//Graph Line Color
                data: values2,
            }],
        },
        options: {
            title: {
                    display: true,
                    text: "Teplota"
                },
            maintainAspectRatio: false,
            elements: {
            line: {
                    tension: 0.5 //Smoothening (Curved) of data lines
                }
            },
            scales: {
                    yAxes: [{
                        ticks: {
                            beginAtZero:true
                        }
                    }]
            }
        }
    });

}

//On Page load show graphs
window.onload = function() {
	console.log(new Date().toLocaleTimeString());
	showGraph(5,10,4,58);
};


setInterval(function() {
  // Call a function repetatively
  getData();
}, 5000); //update rate
var lastTime = 0;
function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
     //Push the data in array
	var ADCValue = this.responseText;
    var lines = ADCValue.split("\n");
    var lastLine = lines[lines.length-2];
    var time = lastLine.split(",")[0];
    var value = lastLine.split(",")[1];
    var value2 = lastLine.split(",")[2];
    if(lastTime == time){
        return;
    }
    lastTime = time;
      values.push(value);
      timeStamp.push(time);
      values2.push(value2);
      showGraph();	//Update Graphs
	//Update Data Table
	  var table = document.getElementById("dataTable");
	  var row = table.insertRow(1);	//Add after headings
	  var cell1 = row.insertCell(0);
	  var cell2 = row.insertCell(1);
      var cell3 = row.insertCell(2);
	  cell1.innerHTML = time;
	  cell2.innerHTML = value;
      cell3.innerHTML = value2;
    }
  };
  xhttp.open("GET", "readADC", true);	//Handle readADC server on ESP8266
  xhttp.send();
}
var values = [];
var timeStamp = [];
function showGraph()
{
    for (i = 0; i < arguments.length; i++) {
    	values.push(arguments[i]);    
    }

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

//Ajax script to get ADC voltage at every 5 Seconds 

setInterval(function() {
  // Call a function repetatively with 5 Second interval
  getData();
}, 2000); //5000mSeconds update rate
 
function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
     //Push the data in array
	var time = new Date().toLocaleTimeString();
	var ADCValue = this.responseText; 
      values.push(ADCValue);
      timeStamp.push(time);
      showGraph();	//Update Graphs
	//Update Data Table
	  var table = document.getElementById("dataTable");
	  var row = table.insertRow(1);	//Add after headings
	  var cell1 = row.insertCell(0);
	  var cell2 = row.insertCell(1);
	  cell1.innerHTML = time;
	  cell2.innerHTML = ADCValue;
    }
  };
  xhttp.open("GET", "readADC", true);	//Handle readADC server on ESP8266
  xhttp.send();
}
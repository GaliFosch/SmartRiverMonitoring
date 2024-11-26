const waterLevelIndex = "http://127.0.0.1:8000/wtld/get-wlevels/"

document.addEventListener("DOMContentLoaded", ()=>{
    const ctx = document
        .getElementById('waterLevelChart')
        .getContext('2d');

    const myChart = new Chart(ctx, {
        type: 'line',
        data: {
            labels: [],
            datasets: [{
                label: 'Real-time Data',
                data: [],
                borderColor: 'rgba(75, 192, 192, 1)',
                backgroundColor: 'rgba(75, 192, 192, 0.2)',
                fill: true,
                lineTension: 0.1
            }]
        },
        options: {
            responsive: true,
            scales: {
                x: { 
                    type: 'linear',
                    title: { 
                        display: true, 
                        text: 'Time' 
                    } 
                },
                y: { 
                    title: { 
                        display: true, 
                        text: 'Level' 
                    } 
                }
            }
        }
    });

    function fetchData() {
        let xhttp = new XMLHttpRequest()
        xhttp.onload = function () {
            let response = JSON.parse(xhttp.responseText)
            // parse elements
            if (response && response.length > 0) {
                myChart.data.labels = [];
                myChart.data.datasets[0].data = [];
    
                for (const measurement of response) {
                    myChart.data.labels.push(measurement['value'].toString());
                    myChart.data.datasets[0].data.push(measurement['timestamp'].toString());
                }
    
                if (response.length > 0) {
                    const lastValue = response[response.length - 1]['value'];
                    document.getElementById('currentWaterLevel').innerText = String(lastValue);
                }
    
                myChart.update();
            }
        }
        xhttp.open("GET", waterLevelIndex, true)
        xhttp.setRequestHeader("Content-Type", "application/json")
        xhttp.send()
    }
    setInterval(fetchData, 5000);

})

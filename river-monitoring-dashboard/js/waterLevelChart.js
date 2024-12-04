

const waterLevelIndex = "http://127.0.0.1:8000/wtld/get-wlevels/"

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
                type: 'time',
                time: {
                    unit: 'second',
                    displayFormats: {
                        second: 'DD HH:mm:ss',
                    }
                },
            },
            y: { 
                title: { 
                    display: true, 
                    text: 'Level' 
                } 
            }
        }
    }
})
fetchData()

function fetchData() {
    let xhttp = new XMLHttpRequest()
    xhttp.onload = function () {
        let response = JSON.parse(xhttp.responseText)
        // parse elements
        console.log(response)
        if (response && response.length > 0) {
            myChart.data.labels = [];
            myChart.data.datasets[0].data = [];

            response.forEach(element => {
                myChart.data.labels.push(convertToISO(element['timestamp']));
                myChart.data.datasets[0].data.push(element['value'].toString());
            })

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
setInterval(fetchData, 1000);


function convertToISO(receivedDate) {
    return receivedDate.replace(' ', 'T')
}

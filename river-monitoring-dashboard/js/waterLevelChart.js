const waterLevelIndex = ""
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
        fetch(waterLevelIndex)
            .then(response => response.json()) 
            .then(newData => {
                myChart.data.labels = [];
                myChart.data.datasets[0].data = [];

                newData.forEach(point => {
                    myChart.data.labels.push(point.x);
                    myChart.data.datasets[0].data.push(point.y);
                });

                if (newData.length > 0) {
                    const lastValue = newData[newData.length - 1].y;
                    document.getElementById('currentWaterLevel').innerText = lastValue;
                }

                myChart.update();
            })
            .catch(error => console.error('Error fetching data:', error));
    }

    // Set interval to periodically fetch and update chart data (e.g., every 5 seconds)
    setInterval(fetchData, 5000);

})

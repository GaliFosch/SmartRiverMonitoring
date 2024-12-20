document.addEventListener("DOMContentLoaded", ()=>{
    const stateIndex = "";
    const stateField = document.getElementById("state");
    function checkState(){
        let xhttp = new XMLHttpRequest()
        xhttp.onload = function () {
            let response = JSON.parse(xhttp.responseText)
            console.log(response)
            if (response && response.length > 0){
                if(response["error"] === 0){
                    stateField.innerText = response["state"]
                }
            }
        }
        xhttp.open("GET", stateIndex, true)
        xhttp.send()
    }
    setInterval(checkState,1000);
})
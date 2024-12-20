document.addEventListener("DOMContentLoaded", ()=>{
    const setOpValUrl = "gti/setOpeningLevel?value="
    const form = document.getElementById("opValForm")
    const input = document.getElementById("opVal")
    form.addEventListener("submit", (event)=>{
        event.preventDefault()
        let xhttp = new XMLHttpRequest()
        let url = setOpValUrl + input.value
        xhttp.open("GET", stateIndex, true)
        xhttp.send()
    })
})
document.addEventListener("DOMContentLoaded", ()=>{
    const setOpValUrl = "http://127.0.0.1:8000/gti/setOpeningLevel?value="
    const form = document.getElementById("opValForm")
    const input = document.getElementById("opVal")
    form.addEventListener("submit", (event)=>{
        event.preventDefault()
        let xhttp = new XMLHttpRequest()
        let url = setOpValUrl + input.value
        try {
            xhttp.open("GET", setOpValUrl, true)
            xhttp.send()   
        } catch (error) {
            console.log("ERROR: Error in send opening vals")
        }
    })
})
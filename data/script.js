fetch("/api/schedule")
    .then(response => response.json())
    .then(data => {
        document.getElementById("patternValue").innerText = data.schedule.value;
    })
    .catch(error => console.log("Error fetching API data:", error));

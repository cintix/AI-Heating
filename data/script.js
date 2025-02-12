fetch("/api/schedule")
    .then(response => response.json())
    .then(data => {
        document.getElementById("patternValue").innerText = data.schedule.value;
    })
    .catch(error => console.log("Error fetching API data:", error));

fetch("/api/schedule")
    .then(response => response.json())
    .then(data => {
        document.getElementById("patternValue").innerText = data.schedule.value;
    })
    .catch(error => console.log("Error fetching API data:", error));

// Handle the datetime picker and send the selected time to the server
document.getElementById("setTimeButton").addEventListener("click", () => {
    const datetimeInput = document.getElementById("datetimePicker").value;

    if (datetimeInput) {
        const selectedDate = new Date(datetimeInput); // Create Date object from the input value
        const unixTimestamp = Math.floor(selectedDate.getTime() / 1000); // Convert to Unix timestamp (seconds)

        // Send the timestamp to the server
        fetch("/api/settime?timestamp=" + unixTimestamp, {
            method: "GET"
        })
            .then(response => response.json())
            .then(data => {
                console.log(data); // Log success or error message from the server
            })
            .catch(error => {
                console.log("Error sending timestamp:", error);
            });
    } else {
        console.log("Please select a valid date and time.");
    }
});

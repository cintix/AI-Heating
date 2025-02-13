// Fetch and display the schedule table
function fetchSchedule() {
    fetch("/api/schedule")
        .then(response => response.json())
        .then(data => {
            document.getElementById("patternValue").innerText = JSON.stringify(data.schedule, null, 2);

            const tableBody = document.querySelector("#scheduleTable tbody");
            tableBody.innerHTML = ""; // Clear existing table rows

            for (let hour = 0; hour < 24; hour++) {
                let row = document.createElement("tr");

                // Hour label
                let hourCell = document.createElement("td");
                hourCell.innerText = hour + ":00";
                row.appendChild(hourCell);

                let maxActivation = 0;
                let maxColumn = -1;

                // Loop through days (Monday to Sunday)
                for (let day = 0; day < 7; day++) {
                    let cell = document.createElement("td");
                    let value = data.schedule[day][hour] || 0; // Ensure default 0
                    cell.innerText = value.toFixed(1);

                    if (value > maxActivation) {
                        maxActivation = value;
                        maxColumn = day;
                    }

                    row.appendChild(cell);
                }

                // Highlight the max value per day
                if (maxColumn !== -1) {
                    row.cells[maxColumn + 1].classList.add("highlight");
                }

                tableBody.appendChild(row);
            }
        })
        .catch(error => console.log("Error fetching API data:", error));
}

// Handle the datetime picker and send the selected time to the server
document.getElementById("setTimeButton").addEventListener("click", () => {
    const datetimeInput = document.getElementById("datetimePicker").value;

    if (datetimeInput) {
        const selectedDate = new Date(datetimeInput);
        const unixTimestamp = Math.floor(selectedDate.getTime() / 1000);

        fetch("/api/settime?timestamp=" + unixTimestamp, { method: "GET" })
            .then(response => response.json())
            .then(data => {
                console.log(data);
            })
            .catch(error => {
                console.log("Error sending timestamp:", error);
            });
    } else {
        console.log("Please select a valid date and time.");
    }
});

// Fetch schedule on page load
fetchSchedule();

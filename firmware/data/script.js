// Get the switch elements
var switch1 = document.getElementById("switch1");
var switch2 = document.getElementById("switch2");
var switch3 = document.getElementById("switch3");

// Get the slider elements
var slider1 = document.querySelector("#switch1 + .slider");
var slider2 = document.querySelector("#switch2 + .slider");
var slider3 = document.querySelector("#switch3 + .slider");

// Function to update the light state based on switch position
function updateLights1() {
  const state = switch1.checked;
  const expectedState = state ? 0 : 1;
  // update the server
  axios
    .get("http://192.168.1.200/toggleswitch1")
    .then((resp) => {
      if (resp.data === expectedState) {
        $("#switch1").prop("checked", !state);
      } else {
        $("#switch1").prop("checked", state);
      }
    })
    .catch((err) => {})
    .finally(() => {
      // change background color
      if (switch1.checked) {
        slider1.style.backgroundColor = "#00ba16"; // Light 1 is on
      } else {
        slider1.style.backgroundColor = "#ccc"; // Light 1 is off
      }
    });
}

function updateLights2() {
  const state = switch2.checked;
  const expectedState = state ? 0 : 1;
  // update the server
  axios
    .get("http://192.168.1.200/toggleswitch2")
    .then((resp) => {
      if (resp.data === expectedState) {
        $("#switch2").prop("checked", !state);
      } else {
        $("#switch2").prop("checked", state);
      }
    })
    .catch((err) => {})
    .finally(() => {
      // change background color
      if (switch2.checked) {
        slider2.style.backgroundColor = "#00ba16"; // Light 1 is on
      } else {
        slider2.style.backgroundColor = "#ccc"; // Light 1 is off
      }
    });
}

function updateLights3() {
  const state = switch3.checked;
  const expectedState = state ? 0 : 1;
  // update the server
  axios
    .get("http://192.168.1.200/toggleswitch3")
    .then((resp) => {
      if (resp.data === expectedState) {
        $("#switch3").prop("checked", !state);
      } else {
        $("#switch3").prop("checked", state);
      }
    })
    .catch((err) => {})
    .finally(() => {
      // change background color
      if (switch3.checked) {
        slider3.style.backgroundColor = "#00ba16"; // Light 1 is on
      } else {
        slider3.style.backgroundColor = "#ccc"; // Light 1 is off
      }
    });
}

// Add event listeners to the switches
switch1.addEventListener("change", updateLights1);
switch2.addEventListener("change", updateLights2);
switch3.addEventListener("change", updateLights3);

// Initial update
loadSwitchStatus();

setInterval(() => {
  loadSwitchStatus();
}, 2000);

function loadSwitchStatus() {
   // $("#switch1").attr("disabled", true);
  // $("#switch2").attr("disabled", true);
  // $("#switch3").attr("disabled", true);
  axios
    .get("http://192.168.1.200/getSwitch1Status")
    .then((resp) => {
      if (resp.data === 1) {
        $("#switch1").prop("checked", true);
      } else if (resp.data === 0) {
        $("#switch1").prop("checked", false);
      }

    })
    .catch((err) => {
      console.log(err);
    })
    .finally(() => {
      $("#switch1").attr("disabled", false);
if (switch1.checked) {
        slider1.style.backgroundColor = "#00ba16"; // Light 1 is on
      } else {
        slider1.style.backgroundColor = "#ccc"; // Light 1 is off
      }
    });

  axios
    .get("http://192.168.1.200/getSwitch2Status")
    .then((resp) => {
      if (resp.data === 1) {
        $("#switch2").prop("checked", true);
      } else if (resp.data === 0) {
        $("#switch2").prop("checked", false);
      }
    })
    .catch((err) => {
      console.log(err);
    })
    .finally(() => {
      $("#switch2").attr("disabled", false);
if (switch2.checked) {
        slider2.style.backgroundColor = "#00ba16"; // Light 1 is on
      } else {
        slider2.style.backgroundColor = "#ccc"; // Light 1 is off
      }
    });

  axios
    .get("http://192.168.1.200/getSwitch3Status")
    .then((resp) => {
      if (resp.data === 1) {
        $("#switch3").prop("checked", true);
      } else if (resp.data === 0) {
        $("#switch3").prop("checked", false);
      }
    })
    .catch((err) => {
      console.log(err);
    })
    .finally(() => {
      $("#switch3").attr("disabled", false);

if (switch3.checked) {
        slider3.style.backgroundColor = "#00ba16"; // Light 1 is on
      } else {
        slider3.style.backgroundColor = "#ccc"; // Light 1 is off
      }

      // update the sync time
      var currentdate = new Date();
      var datetime =
        "Last Sync: " +
        currentdate.getDate() +
        "/" +
        (currentdate.getMonth() + 1) +
        "/" +
        currentdate.getFullYear() +
        " " +
        currentdate.getHours() +
        ":" +
        currentdate.getMinutes() +
        ":" +
        currentdate.getSeconds();

      $(".last-sync").text(datetime);
    });
}

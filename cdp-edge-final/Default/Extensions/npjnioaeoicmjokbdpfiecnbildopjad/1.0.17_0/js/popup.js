$(window).on('load', function(){
  function restore_options() {
    document.getElementById("ua").value = localStorage.getItem('ua') || "default";
    document.getElementById("customua").value = localStorage.getItem('customua') || "your custom user-agent";
  }
  
  restore_options();  
});

$(document).on('change', "select", function() {
  localStorage.setItem('ua', $("#ua").val());
  $("#status")[0].textContent = 'Settings saved!';
  setTimeout(function() {
    $("#status")[0].textContent = '';
  }, 750);
});

$("#save").click(function() {
  let customua = $("#customua").val();
  localStorage.setItem('customua', customua);
  let status2 = document.getElementById('status2');
  status2.textContent = 'Saved!';
  setTimeout(function() { status2.textContent = 'Select Custom User-Agent from above drop-down menu.'; }, 750);
});

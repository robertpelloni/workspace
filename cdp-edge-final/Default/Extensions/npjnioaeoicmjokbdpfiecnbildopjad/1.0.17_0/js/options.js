$(window).on("load", function(){

  function restore_options() {
    document.getElementById("customua").value = localStorage.getItem('customua') || "your custom user-agent";
  }

	// save the custom User-Agent
	$("#save").click(function() {
    localStorage.setItem('customua', $("#customua").val());
    let status = document.getElementById('status');
    status.textContent = 'Options saved.';
    setTimeout(function() { status.textContent = ''; }, 750);
  });

  restore_options();
});
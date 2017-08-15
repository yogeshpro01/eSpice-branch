toplist = ["Home", "Learn" ,"Documentation", "Updates", "Interpreters"]
$(".bar").append('<div class="topbar"><div class="rightlist"></div></div>')
for (var i = 0; i < toplist.length; i++) {
	$(".rightlist").append('<div class="list" id="'+ toplist[i] +'">'+ toplist[i] +'</div>')
	
}


$(document).ready(function() {
	$('#msg1').click(function(event) {
//		jQuery.post('./jaxer-service/service',
//		jQuery.post('./service',
		jQuery.post('D:/PersonalTool/xyzzy/laboratory/JavaScript/jQuery/service',
					{ id:$('#input').val(), col:$('#col').val() },
					function(data) {
						$('#target').text(data);
					},
					'text');
	});
});

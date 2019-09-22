$(document).ready(function(){
	$.ajax({
		url : "followersdata.php",
		type : "GET",
		success : function(data){
			console.log(data);

			var time = [];
			var dust_value = [];
			var nh4_value = [];
			var ethanol_value = [];
			var acetone_value = [];
			var toulene_value = [];
			var co_value = [];
			var co2_value=[];

			for(var i in data) {
				time.push("Date " + data[i].date);
				dust_value.push(data[i].Dust);
				nh4_value.push(data[i].NH4);
				ethanol_value.push(data[i].Ethanol);
				acetone_value.push(data[i].Acetone);
				toulene_value.push(data[i].Toulene);
				co_value.push(data[i].CO);
				co2_value.push(data[i].CO2);
			}

			var chartdata = {
				labels: time,
				datasets: [
					{
						label: "Dust",
						fill: false,
						lineTension: 0.1,
						backgroundColor: "rgba(59, 89, 152, 0.75)",
						borderColor: "rgba(59, 89, 152, 1)",
						pointHoverBackgroundColor: "rgba(59, 89, 1521)",
						pointHoverBorderColor: "rgba(59, 89, 152, 1)",
						data: dust_value
					},
					{
						label: "NH4",
						fill: false,
						lineTension: 0.1,
						backgroundColor: "rgba(29, 202, 255, 0.75)",
						borderColor: "rgba(29, 202, 255, 1)",
						pointHoverBackgroundColor: "rgba(29, 202, 251)",
						pointHoverBorderColor: "rgba(29, 202, 255, 1)",
						data: nh4_value
					},
					{
						label: "Ethanol",
						fill: false,
						lineTension: 0.1,
						backgroundColor: "rgba(211, 72, 54, 0.75)",
						borderColor: "rgba(211, 72, 54, 1)",
						pointHoverBackgroundColor: "rgba(211, 72, 541)",
						pointHoverBorderColor: "rgba(211, 72, 54, 1)",
						data: ethanol_value
						
					},
					{
						label: "Acetone",
						fill: false,
						lineTension: 0.1,
						backgroundColor: "rgba(0, 255, 0, 0.75)",
						borderColor: "rgba(0, 255, 0, 1)",
						pointHoverBackgroundColor: "rgba(0, 255, 0, 1)",
						pointHoverBorderColor: "rgba(0, 255, 0, 1)",
						data: acetone_value
						
					},
					{
						label: "Toulene",
						fill: false,
						lineTension: 0.1,
						backgroundColor: "rgba(255, 255, 51, 0.75)",
						borderColor: "rgba(255, 255, 51, 1)",
						pointHoverBackgroundColor: "rgba(255, 255, 51)",
						pointHoverBorderColor: "rgba(255, 255, 51, 1)",
						data: toulene_value
						
					},
					{
						label: "CO",
						fill: false,
						lineTension: 0.1,
						backgroundColor: "rgba(0, 0, 0, 0.75)",
						borderColor: "rgba(0, 0, 0, 1)",
						pointHoverBackgroundColor: "rgba(0, 0, 0, 1)",
						pointHoverBorderColor: "rgba(0, 0, 0, 1)",
						data: co_value
						
					},
					{
						label: "CO2",
						fill: false,
						lineTension: 0.1,
						backgroundColor: "rgba(139, 89, 4, 0.96)",
						borderColor: "rgba(139, 89, 4, 1)",
						pointHoverBackgroundColor: "rgba(139, 89, 4, 1)",
						pointHoverBorderColor: "rgba(139, 89, 4, 1)",
						data: co2_value
						
					}
				]
			};

			var ctx = $("#mycanvas");

			var LineGraph = new Chart(ctx, {
				type: 'line',
				data: chartdata
			});
		},
		error : function(data) {

		}
	});
});

<?php
$servername = "localhost";
$username = "username";
$password = "password";
$dbname = "database";
date_default_timezone_set('Asia/Kathmandu');
$date = date('Y-m-d h:i:s A');
//mysql_query("INSERT INTO `table` (`dateposted`) VALUES ('$date')");

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "INSERT INTO database.table1 (date,Dust, NH4, Ethanol, Acetone, Toulene, CO,CO2) VALUES ('".$date."','".$_GET['Dust']."', '".$_GET['NH4']."', '".$_GET['Ethanol']."', '".$_GET['Acetone']."', '".$_GET['Toulene']."', '".$_GET['CO']."','".$_GET['CO2']."');";

if ($conn->query($sql) === TRUE) {
    echo "New record created successfully";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();
?>

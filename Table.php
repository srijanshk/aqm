<!DOCTYPE html>
<html>
<head><meta http-equiv="refresh" content="3" ></head>
<center>
<body>


<?php
$con=mysqli_connect("localhost","username","password","database");
// Check connection
if (mysqli_connect_errno())
{
echo "Failed to connect to MySQL: " . mysqli_connect_error();
}

$result = mysqli_query($con,"SELECT id,date, Dust,NH4,Ethanol,Acetone,Toulene,CO,CO2 FROM table1 ORDER BY id DESC");

echo "<table border='3'>
<tr>
<th>Id</th>
<th>date</th>
<th>Dust(mg/m^3)</th>
<th>NH4(ppm)</th>
<th>Ethanol(ppm)</th>
<th>Acetone(ppm)</th>
<th>Toulene(ppm)</th>
<th>CO(ppm)</th>
<th>CO2(ppm)</th>
</tr>";
$counter = 1;
while($row = mysqli_fetch_array($result))
{
echo "<tr>";
//echo $counter;

echo "<td>" . $counter . "</td>";
echo "<td>" . $row['date'] . "</td>";
echo "<td>" . $row['Dust'] . "</td>";
echo "<td>" . $row['NH4'] . "</td>";
echo "<td>" . $row['Ethanol'] . "</td>";
echo "<td>" . $row['Acetone'] . "</td>";
echo "<td>" . $row['Toulene'] . "</td>";
echo "<td>" . $row['CO'] . "</td>";
echo "<td>" . $row['CO2'] . "</td>";
echo "</tr>";
$counter++;
}
echo "</table>";

mysqli_close($con);
?>
</body>
</html>

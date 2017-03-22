<?php
	include("conecta.php");

	$sensor1 = $_GET['sensor1'];

	$sql_insert = "insert into tabelaarduino(sensor1) values('$sensor1')";

	mysqli_query($conexao,$sql_insert);

	if($sql_insert){
		echo "salvo com sucesso";
	}else{
		echo "houve um erro";
	}

?>
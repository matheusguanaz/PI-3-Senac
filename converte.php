<?php

include("conecta.php");




// x = 2121212121 aquele numero enorme, data em formato uinix
	// y = valor
$stid = mysqli_query($conexao, "select  evento,sensor1 from tabelaarduino");
	$dias_values = array();

while ( $linha = mysqli_fetch_array($stid, MYSQL_BOTH)) {


		if($linha > 0) {
			array_push( $dias_values, array( ( (int) strtotime( $linha['evento']." - 3 hours" )*1000 ), (int)$linha['sensor1'] ) );
			$linha++;
		}
		$linha++;
	}

array_push( $dias_values, array( ( (int) strtotime( $row['evento']." - 3 hours" )*1000 ), (int)$value2 ) );

echo json_encode($dias_values);

?>

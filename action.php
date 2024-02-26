<?php
    if($_SERVER["REQUEST_METHOD"] == "POST"){

        $name = $_POST["name"];
        $email = $_POST["email"];
        $message = $_POST["message"];

        $response = array(
            "status" => "success",
            "message" => "Grazie per averci contattato. Ti risponderemo il prima possibile."
        );

        header('Content-Type: application/json');
        echo json_encode($response);
    }else{
        $response = array(
            "status" => "error",
            "message" => "Il form non è stato inviato correttamente."
        );

        header('Content-Type: application/json');
        echo json_encode($response);
    }
?>

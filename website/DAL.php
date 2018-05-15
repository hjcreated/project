<?php
/**
 * Created by PhpStorm.
 * User: hj
 * Date: 8/16/2017
 * Time: 2:43 AM
 * Class used to connect the database with the class BL
 */

class DAL
{

    public $conn;

    function __construct($servername, $username, $password, $dbname)
    {
        $this->createConnection($servername, $username, $password, $dbname);

    }


    function createConnection($servername, $username, $password, $dbname)
    {
        // Create connection
        $this->conn = new mysqli($servername, $username, $password, $dbname);
        // Check connection
        if ($this->conn->connect_error) {
            die("Connection failed: " . $this->conn->connect_error);
        }
    }


    function executeSelect($sql=null)
    {
        $result = $this->conn->query($sql);
        return $result;
    }
    function executeDML($sql=null)
    {
        return ($this->conn->query($sql)=== TRUE) ;

    }

}
<?php
/**
 * Created by PhpStorm.
 * User: hj
 * Date: 8/16/2017
 * Time: 2:43 AM
 * All methods used to connect to the database.
 */

require_once "BL.php";
class patientListC
{
    public $bl;
    public $name;
    public $id;

    /**
     * patientListC constructor.

     */
    public function __construct()
    {
        $this->bl = new BL();
    }


    public function  retrieveList(){
    $this->bl->retrieveList();
    }





}//end class
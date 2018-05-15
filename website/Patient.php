<?php
/**
 * Created by PhpStorm.
 * User: hj
 * Date: 8/16/2017
 * Time: 2:43 AM
 * All methods used to connect to the database.
 */

require_once "BL.php";
class Patient
{
    public $bl;
    public $name;
    public $id;

    /**
     * Patient constructor.
     * used to Create new Patient.
     * @param $_name
     * @param $_id
     */
    function __construct($_name,$_id)
    {
       $this->name=$_name;
       $this->id=$_id;
      $this->bl= new BL();
    }//construct

    /**
     * add new patient
     * @param $id
     * @param $name
     * @param $age
     * @param $sex
     * @param $illness
     * @return mixed
     */
    function addPatient($id, $name, $age, $sex, $illness){
       return $this->bl->addPatient($id,$name,$age,$sex,$illness);
    }







}//end class
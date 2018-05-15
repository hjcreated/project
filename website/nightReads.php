<?php
/**
 * Created by PhpStorm.
 * User: hj
 * Date: 5/5/2018
 * Time: 2:34 AM
 */
require_once "BL.php";

class nightReads
{
    public $id;
    public $time;
    public $medicine;
    public $dose;
    public $bl;

    /**
     * nightReads constructor.
     * @param $_id
     * @param $_medicine
     * @param $_dose
     */
    function __construct($_id, $_medicine, $_dose)
    {
        $this->id=$_id;
        $this->medicine=$_medicine;
        $this->dose=$_dose;
        $this->time=date("h:i:sa");
        $this->bl= new BL();
    }//construct

    /**
     * add new night shift reads
     * @param $id
     * @param $medicine
     * @param $Dose
     * @return mixed
     */
    public function addNightReads($id, $medicine, $Dose){
        return $this->bl->addNightReads($id,$medicine,$Dose);
    }


    /**
     * check the id of the patient before adding it
     * @param $id
     * @return mixed
     */
    public function checkId($id){
        return $this->bl->checkId($id);
    }
}// class
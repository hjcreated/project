<?php
/**
 * Created by PhpStorm.
 * User: hj
 * Date: 8/16/2017
 * Time: 2:43 AM
 * All methods used to connect to the database.
 */

require_once "DAL.php";
class BL
{
    public $dal;

    /**
     * BL constructor.
     * used to start connection with DataBase.
     */
    function __construct()
    {
        $this->dal=new DAL("localhost","root","","shb");
    }//construct


    /**
     * used to check the user in case of login
     * @param $Email
     * @param $password
     * @return mixed
     */
    public function login($Email, $password)
    { $sql2 = "select * from nurse WHERE Email='".$Email ."'and Password='".$password ."'";
        return $result= $this->dal->executeSelect($sql2);
    }

    /**
     * create new user and check the email
     * @param $Name
     * @param $Email
     * @param $Password
     * @param $Gender
     * @return mixed
     */
    public function SignUp($Name, $Email, $Password, $Gender)
    { $sql = "INSERT INTO nurse(Name,Email,Password,Gender)".
        "VALUES ('".$Name."','".$Email."','".$Password."','".$Gender."');";
        return $this->dal->executeSelect($sql);
    }

    /**
     * add new patient
     * @param $id
     * @param $name
     * @param $age
     * @param $sex
     * @param $illness
     * @return mixed
     */
    public function addPatient($id, $name, $age, $sex, $illness)
    {$sql= "insert into Patients VALUES(".$id.",'".$name."',".$age.",'".$sex."','".$illness."'); ";
    return $this->dal->executeSelect($sql);
    }

    /**
     * add new night reads
     * @param $id
     * @param $medicine
     * @param $Dose
     * @return mixed
     */
    public function addNightReads($id, $medicine, $Dose){
        $sql="insert into nightReads (id,medicine,dose) VALUES (".$id.",'".$medicine."','".$Dose."');";
        return $this->dal->executeSelect($sql);
    }

    /** check the id of the patient before adding it
     * @param $id
     * @return mixed
     */
    public function checkId($id){
        $sql= "select id from Patients where id=".$id;
        return $this->dal->executeSelect($sql);
    }

    /**
     * this  method is used to retrieve all the patient in the patients database table
     * @return mixed
     */
    public function retrieveList(){
        $sql = "select * from patients";
        return $this->dal->executeSelect($sql);
    }







}//end class
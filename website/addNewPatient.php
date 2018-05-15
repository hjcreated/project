<?php
/**
 *
 * Created by PhpStorm.
 * User: hj
 * Date: 5/5/2018
 * Time: 12:33 AM
 */
session_start();
$name = $_SESSION['regName'];
if(!isset($_SESSION['regName']))
{
    header("location:login.php");
}
?>
<html>
<head>
    <?php
    include "links.php";
    ?>

    <title>new patient</title>
    <link rel="icon" type="image/png" href="pics/logo2.png" sizes="16x16">
    <script>
        $(document).ready(function(){
            $("#errorMsg").hide();
            $("#conMsg").hide();
        });
    </script>


</head>
<body>
<form method="get">

    <!-- ========================= NAVBAR ================================================-->
    <!-- ========================= NAVBAR ================================================-->
    <section id="header"><nav  class="navbar navbar-expand-lg fixed-top " id="nav" style="height:60px ">
        <div class="container">
            <button class="navbar-brand"  id="logout" name="logout" style=" height: 50px;  background-color: transparent;border-color: transparent">Logout <i class="fa fa-sign-out" aria-hidden="true" style="font-size:18px"></i></button>
            <button class="navbar-brand"  id="Home" name="Home" style=" height: 50px;  background-color: transparent;border-color: transparent">Home <i class="fa fa-home" aria-hidden="true" style="font-size:18px" ></i></button>
            <ul >
                <!----><li >
                    <a  class="navbar-brand"  href="" rel="tooltip"  >
                        <i  class="fa fa-twitter " style="font-size:18px;" ></i>

                    </a>
                </li>
                <!----><li>
                    <a  class="navbar-brand"  href="" rel="tooltip" >
                        <i  class="fa fa-facebook-square " style="font-size:18px;"></i>

                    </a>
                </li>
                <!----><li >
                    <a  class="navbar-brand"  href="" rel="tooltip" >
                        <i  class="fa fa-instagram " style="font-size:18px;"></i>

                    </a>
                </li>
                <!----><li>
                    <a  class="navbar-brand"  href="" rel="tooltip" >
                        <i  class="fa fa-github " style="font-size:18px;"></i>
                    </a>
                </li>
                <!----><li  >
                    <a  class="navbar-brand"  href="index.php"  >
                        <i class="nc-icon nc-book-bookmark" style="font-size:18px;"></i>
                        Documentation</a>
                </li>

                <!---->
                <!---->
            </ul>

        </div>
    </nav></section>
    <?php
    // ========= this function used to logout from the system ===========
    if(isset($_GET['logout'])) {
        session_destroy(); // destroy the session
        echo "<script type='text/javascript'>  window.location='index.php'; </script>"; // redirect to index page
    }//if is set

    // ========= if home button pressed ===========
    if(isset($_GET['Home'])) {
        echo "<script type='text/javascript'>  window.location='profile.php'; </script>"; // redirect to home page
    }//if is set
    ?>
</form>
    <!-- ======================================= Background  ================================ -->
<form method="get">
<section id="form"><div id="firstPage" class="page-header section-dark" style="background-color: white;">
        <div class="centerDiv" align="center">
            <div class="loginDivBlack" align="center" id="loginDivBlack" style="height: 80%; width:40%">
                <h4>New Patient Record</h4><br>
                <img alt="Rounded Image" class="img-circle img-no-padding img-responsive" src="pics/patient_logo.png" style="width: 60px;height: 60px" ><br>
                <input type="text" id="Name"  name="Name" placeholder="Full Name" class="form-control" style=" width:80%;background: rgba(204, 204, 204, 0.0);color: white; text-align: center " required >
                <input type="text" id="id"  name="id"  placeholder="Patient's ID" class="form-control" style="text-align: center; width:80%;background: rgba(204, 204, 204, 0.0);color: white; margin-top: 5px;margin-bottom: 5px" required >
                <input type="text" id="age" name="age" placeholder="age" class="form-control" style=" text-align: center;width:80%;background: rgba(204, 204, 204, 0.0);color: white" required>
                <h5>Gender</h5>
                <label for="gender"></label>
                <input type="radio"  name="gender"   id="gender" value ="Male" class="form-control-input" style=" text-align: center;background: rgba(204, 204, 204, 0.0);color: white"><label>Male</label>&nbsp;&nbsp;&nbsp;
                <input type="radio"  name="gender"   id="gender" value="Female" class="form-control-input" style=" text-align: center;background: rgba(204, 204, 204, 0.0);color: white"><label>Female</label>
                <input type="text" id="illness"  name="illness"  placeholder="illness" class="form-control" style="text-align: center; width:80%;background: rgba(204, 204, 204, 0.0);color: white; margin-top: 5px;margin-bottom: 5px" required>
                <input type="submit" class="form-control" value="Submit" id="submit" name="submit" style="text-align: center; width:50%;background: rgba(204, 204, 204, 0.0);color: white "><br>
                <h5 style="margin-top: 1px; color:red;" id="errorMsg">Check the ID & try again</h5> <!--Error msg to be displayed incase of error -->
                <h5 style="margin-top: 1px; color:blue;" id="conMsg">New recored has been added</h5><!-- Confirmation msg new record has been added -->
            </div>
        </div>
        <h6  class=" category-absolute ml-auto mr-auto">SHB Team @University of Petra</h6>
    </div></section>

    <?php

    // =================== create new user when submit is clicked ===============
    if(isset($_GET['submit'])) {

        $name = $_GET['Name']; // hold the value of the name
        $id = $_GET['id']; // hold the name of the id
        $age = $_GET['age']; // hold the value of the age
        $sex = $_GET['gender']; // hold the value of the gender
        $illness = $_GET['illness']; // hold the value of the illness
        include "BL.php"; // include bl class to use the methods inside of it
        $bl = new BL(); // create new object of the class
        if($bl->addPatient($id,$name,$age,$sex,$illness)){ // if add patient success
            //display confirm msg
            echo "<script src=\"js/confirm.js\"></script>";
        }//if true
        else{
            //make div vibrate and display error msg
            echo "<script src=\"js/vibrate.js\"></script>";

        }//else

    }//if is set




    ?>



</form>
</body>
</html>

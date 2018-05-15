<?php
session_start();
$name = $_SESSION['regName'];
$position = $_SESSION['position'];
$email=$_SESSION['email'];
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
    <title>Profile</title>
    <link rel="icon" type="image/png" href="pics/logo2.png" sizes="16x16">

</head>
<body>
<form method="get">

    <!-- ========================= NAVBAR ================================================-->
    <a name="#top"></a>
    <nav  class="navbar navbar-expand-lg fixed-top " id="nav" style="height:60px ">
        <div class="container">
            <button class="navbar-brand"  id="logout" name="logout" style=" height: 50px;  background-color: transparent;border-color: transparent">Logout <i class="fa fa-sign-out" aria-hidden="true" style="font-size:18px"></i></button>
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
    </nav>

    <!-- ======================================= Background of the FIRST page of the Index ================================ -->

    <div id="firstPage" class="page-header section-dark" style=" background-color: white;">

        <div class="centerDiv" align="center">
            <div  align="center" style="height: 100%; width:65%;margin-top: 5%;background: url(<?php if($email=="Alaa@SmartHB.jo"){ echo 'pics/alaa.png';} else{echo 'pics/user.png';} ?>) no-repeat;  " >
                <br><br><br><br>
                <div class="container-fluid" style="float:left; margin-left:450px;" align="left">
                    <h3><?php echo $name; ?></h3>
                    <br>
                    <h3><?php echo $position; ?></h3>
                </div>
            </div>
        </div>
        <div style="height: 100%;width: 20%;margin-left: -100px" >
            <br><br><br><br><br><br><br><br><br>
            <button class="btn btn-outline-default btn-round" type="submit" style="margin-left: -80px " >Patient List</button><br><br><br>
            <button class="btn btn-outline-default btn-round" type="submit" style="margin-left: -80px" id="nightReads" name="nightReads">Add Night-shift read</button><br><br><br>
            <button class="btn btn-outline-default btn-round" type="submit" style="margin-left: -80px" id="newPatient" name="newPatient">Add new Patient</button><br>
        </div>

    </div>
    <?php
    // ========= this function used to logout from the system ===========
    if(isset($_GET['logout'])) {
        session_destroy(); // destroy the created session
        echo "<script type='text/javascript'>  window.location='index.php'; </script>";

    }//if is set


    // ========= go to create new patient page ===========
    if(isset($_GET['newPatient'])) {
        echo "<script type='text/javascript'>  window.location='addNewPatient.php'; </script>";
    }//if is set

    // ========= go to create add night reads page ===========
    if(isset($_GET['nightReads'])) {
        echo "<script type='text/javascript'>  window.location='addNightReads.php'; </script>";
    }//if is set
    ?>


</form>
</body>
</html>
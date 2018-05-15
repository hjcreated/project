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
    <title>Patient List</title>
    <link rel="icon" type="image/png" href="pics/logo2.png" sizes="16x16">
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
            <div class="centerDiv" align="center" >
                <br><br><br><br><br><br>


                <table style=" width:60%;"  >
                    <tr><th>ID</th><th>Name</th><th>Age</th><th>Sex</th><th>Illness</th><th>Edit</th></tr>
                <?php

                // =================== Load Patient list table on page load ===============
                include "BL.php";
                $bl = new BL();
                $result=$bl->retrieveList();
                    while ($row = $result->fetch_assoc()) {
                        $id = $row['Id'];
                        $name = $row['Name'];
                        $Age=$row['Age'];
                        $Sex=$row['Sex'];
                        $illness=$row['ilness'];
                          echo "<tr><td >".$id."</td><td>".$name."</td><td>".$Age."</td><td>".$Sex."</td><td>".$illness."</td><td><button  id=\"Edit\" name=\"Edit\"  class=\"editButton\" value=\".$id.\"> Edit <i class=\"fa fa-pencil-square-o\" aria-hidden=\"true\"></i></button></td></tr>";
                       }

                       if(isset($_GET['Edit'])){
                        $_SESSION['id']=$id;


                       }



                ?>
                </table>
            </div>
        </div></section>





</form>
</body>
</html>

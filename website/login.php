<?php
session_start();
?>
<html>
<head>
    <?php
    include "links.php";
    ?>

   <title>Login</title>
    <link rel="icon" type="image/png" href="pics/logo2.png" sizes="16x16">
    <script>
        $(document).ready(function(){
            $("#errorMsg").hide();
        });
    </script>
</head>
<body>
<form method="get" ">

<!-- ========================= NAVBAR ================================================-->
<a name="#top"></a>
<nav  class="navbar navbar-expand-lg fixed-top navbar-transparent" id="nav">
    <div class="container">
            <a class="navbar-brand" href="newAccount.php" >Create new Account <i class="fa fa-user-md" aria-hidden="true" style="font-size:25px"></i></a>
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
<div id="firstPage" class="page-header section-dark" style="background-image: url('pics/background4.jpg')">
    <div class="centerDiv" align="center" >
        <div class="loginDivBlack" align="center" id="loginDivBlack" >
            <br><br>
         <h5>Welcome</h5>
            <div  class="social-line text-center">
                <a  class="btn btn-neutral btn-facebook btn-just-icon" href="#">
                    <i  class="fa fa-facebook-square"></i>
                </a>
                <a  class="btn btn-neutral btn-google btn-just-icon" href="#">
                    <i  class="fa fa-google-plus"></i>
                </a>
                <a  class="btn btn-neutral btn-twitter btn-just-icon" href="#">
                    <i  class="fa fa-twitter"></i>
                </a>
            </div>
            <h5 style="float: left;margin-left:33px">Email</h5><br>
            <input type="text" id="email" name="email" placeholder="Email" class="form-control" style="width:80%;background: rgba(204, 204, 204, 0.0);color: white">

            <h5 style="float: left;margin-left:33px;margin-top: 3px">Password</h5><br>
            <input type="password" id="password" name="password" placeholder="Password" class="form-control" style="width:80%;background: rgba(204, 204, 204, 0.0);color: white"><br>
            <input type="submit" class="form-control" value="LOGIN" id="loginBtn" name="loginBtn" style="width:40%;background: rgba(204, 204, 204, 0.0);color: white "><br>
            <h5 style="margin-top: 1px">Forget your Password?</h5>
            <img src="pics/heartPulse.gif" style=" height: 10%;width: 30%;margin-left: 30px">
            <h5 style="margin-top: 1px; color:red;" id="errorMsg">Wrong Email or Password</h5>



        </div>
      </div>
    <h6  class=" category-absolute ml-auto mr-auto">SHB Team @University of Petra</h6>
</div>


    <?php

    if(isset($_GET['loginBtn'])) {
         $email = $_GET['email'];// hold the value of the email
         $password = $_GET['password']; // hold the value of the password
         include "BL.php"; // include bl to use the method login
         $bl = new BL(); // new object from bl class
         $result=$bl->login($email,$password); // call the login method

         if ($bl->login($email,$password)->num_rows){ // if login succeed

             while ($row = $result->fetch_assoc()) {

                 $name = $row['Name']; // fitch the name from the database to be sed to the other page
                 $position = $row['Position']; // fitch the position
                 $Email = $row['Email']; // fitch the email
                 $_SESSION['regName']=$name; // send the name to profile page
                 $_SESSION['position']=$position; // send position to profile page
                 $_SESSION['email']=$Email; // send the email

             }//while
               /// redirect to profile page
             echo "<script type='text/javascript'>  window.location='profile.php'; </script>";
         }//if login
        else{
             //make div vibrate and display error msg
             echo "<script src=\"js/vibrate.js\"></script>";

        }

    }//if is set
    ?>

 </form>
</body>
</html>


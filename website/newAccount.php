<html>
<head>
    <?php
    include "links.php";
    ?>

    <title>new User</title>
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
    <a name="#top"></a>
    <nav  class="navbar navbar-expand-lg fixed-top navbar-transparent" id="nav">
        <div class="container">
            <a class="navbar-brand" href="login.php" id="login" name="login"><span style="color: #014c8c">already have an Account?</span> login <i class="fa fa-sign-in" aria-hidden="true" style="font-size:25px"></i></a>
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
    <!-- ======================================= Background  ================================ -->
    <div id="firstPage" class="page-header section-dark" style="background-image: url('pics/background5.jpg')">
        <div class="centerDiv" align="center">
            <div class="loginDivBlack" align="center" id="loginDivBlack">
                <h4>Welcome</h4><br>
                <img alt="Rounded Image" class="img-circle img-no-padding img-responsive" src="pics/userIcon.png" style="width: 60px;height: 60px"><br>
                <input type="text" id="Name"  name="Name" placeholder="Full Name" class="form-control" style="width:80%;background: rgba(204, 204, 204, 0.0);color: white" required>
                <input type="email" id="email"  name="email"  placeholder="Email" class="form-control" style="width:80%;background: rgba(204, 204, 204, 0.0);color: white; margin-top: 5px;margin-bottom: 5px" required>
                <input type="password" id="password" name="password" placeholder="Password" class="form-control" style="width:80%;background: rgba(204, 204, 204, 0.0);color: white" required>
                <h5>Gender</h5>
                <label for="gender"></label>
                <input type="radio"  name="gender"   id="gender" value ="Male" class="form-control-input" style="background: rgba(204, 204, 204, 0.0);color: white"><label>Male</label>&nbsp;&nbsp;&nbsp;
                <input type="radio"  name="gender"   id="gender" value="Female" class="form-control-input" style="background: rgba(204, 204, 204, 0.0);color: white"><label>Female</label>
                <input type="submit" class="form-control" value="Submit" id="sigup" name="signup" style=" width:50%;background: rgba(204, 204, 204, 0.0);color: white "><br>
                <h5 style="margin-top: 1px; color:red;" id="errorMsg">Check the info & try again</h5>
                <h5 style="margin-top: 1px; color:blue;" id="conMsg">User has been Created</h5>
            </div>
        </div>
        <h6  class=" category-absolute ml-auto mr-auto">SHB Team @University of Petra</h6>
    </div>


    <?php
    if(isset($_GET['signup'])) {


        $email = $_GET['email'];
        $password = $_GET['password'];
        $name = $_GET['Name'];
        $Gender = $_GET['gender'];
        include "BL.php";
        $bl = new BL();
    if($bl->SignUp($name,$email,$password,$Gender)){
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
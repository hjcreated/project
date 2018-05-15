
    $(function () {
        var i = 0;
        while (i < 2) {

            $("#loginDivBlack").animate({
                marginLeft: "10px",
            }, 50);

            $("#loginDivBlack").animate({
                marginLeft: "-10px",
            }, 50);

            $("#loginDivBlack").animate({
                marginLeft: "10px",
            }, 50);
            i++;
        }
        $("#errorMsg").show();
    });


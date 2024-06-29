let element = document.getElementById("button_cool");
let date_name = document.getElementById("dater");

element.onclick = () => 
{
    let current_date = new Date();
    date_name.innerText = current_date.toDateString();
}
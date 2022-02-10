console.log(getPhoneNumberList());

function getPhoneNumberList(){
  fetch("./phone_numbers.json")
  .then(list => {
    return list.json();
  })
}
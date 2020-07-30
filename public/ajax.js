function call(data){
  
  // 입력값을 변수에 담고 문자열 형태로 변환
  var data = {'email' : data};
  data = JSON.stringify(data);

  // content-type을 설정하고 데이터 송신
  var xhr = new XMLHttpRequest();
  xhr.open('POST', 'http://127.0.0.1:3000/ajax_send_email');
  xhr.setRequestHeader('Content-type', "application/json");
  xhr.send(data);
}
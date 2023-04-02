function choiceAnswer(button) {
    if (button.value == 'correct'){
        button.style.backgroundColor='green';
        document.querySelector('#result_choice').textContent='Correct!';
    }
    else{
        button.style.backgroundColor='red';
        document.querySelector('#result_choice').textContent='InCorrect!';
    }
    document.querySelectorAll('button').forEach(function(btn) {
    btn.disabled = true;});
}

function inputAnswer(){
    var inputtext = document.querySelector('input').value
    if (inputtext.toLowerCase() == 'zelda'){
        document.querySelector('#result_input').textContent='Correct!'
        document.querySelector('#result_input').style.color='green' 
    }
    else{
        document.querySelector('#result_input').textContent='InCorrect!'
        document.querySelector('#result_input').style.color='red'
    }
}
// ==UserScript==
// @name         湖州师范学院校园网自动登录
// @namespace    hzsf
// @version      2024-05-27
// @description  校园网自动登录
// @author       kun
// @match        http://172.20.6.53/eportal/*
// @match        https://rz.zjhu.edu.cn/cas/*
// @match        https://rz.zjhu.edu.cn:4433/*
// @grant        GM_getValue
// @grant        GM_setValue
// @icon         https://www.zjhu.edu.cn/_upload/tpl/00/0b/11/template11/favicon.ico
// ==/UserScript==

(function() {
    'use strict';
    // 读取存储的用户名和密码，如果不存在则提示用户输入
    let username = GM_getValue('username', null);
    let password = GM_getValue('password', null);
    inputNumber();
    function inputNumber(){
        var rectangle = document.createElement('div');
        rectangle.style.position = 'fixed';
        rectangle.style.top = '10px'; // 初始位置在左上角
        rectangle.style.left = '10px'; // 初始位置在左上角
        rectangle.style.width = '300px';
        rectangle.style.height = '200px';
        rectangle.style.backgroundColor = '#f0f0f0';
        rectangle.style.border = '1px solid #ccc';
        rectangle.style.padding = '20px';
        rectangle.style.boxShadow = '0 0 10px rgba(0, 0, 0, 0.1)';
        rectangle.style.cursor = 'move'; // 设置鼠标样式为可拖动
        rectangle.draggable = true; // 设置元素为可拖动
        document.body.appendChild(rectangle);

        // 创建用户名输入框
        var usernameInput = document.createElement('input');
        usernameInput.id = 'username1';
        usernameInput.type = 'text';
        usernameInput.placeholder = '用户名';
        rectangle.appendChild(usernameInput);

        // 创建密码输入框
        var passwordInput = document.createElement('input');
        passwordInput.id = 'password1';
        passwordInput.type = 'password';
        passwordInput.placeholder = '密码';
        rectangle.appendChild(passwordInput);

        // 创建保存按钮
        var saveButton = document.createElement('button');
        saveButton.textContent = '保存';
        rectangle.appendChild(saveButton);

        // 鼠标按下时记录初始位置和鼠标位置
        var offsetX, offsetY;
        rectangle.addEventListener('mousedown', function(e) {
            offsetX = e.clientX - rectangle.getBoundingClientRect().left;
            offsetY = e.clientY - rectangle.getBoundingClientRect().top;
        });

        // 鼠标移动时更新矩形范围的位置
        document.addEventListener('mousemove', function(e) {
            if (offsetX !== undefined && offsetY !== undefined) {
                rectangle.style.left = (e.clientX - offsetX) + 'px';
                rectangle.style.top = (e.clientY - offsetY) + 'px';
            }
        });

        // 鼠标松开时清除记录
        document.addEventListener('mouseup', function() {
            offsetX = undefined;
            offsetY = undefined;
        });

        // 点击按钮时执行的函数
        saveButton.addEventListener('click', function() {
            var username = document.getElementById('username1').value;
            var password = document.getElementById('password1').value;

            // 存储用户名和密码
            if (username && password) {
                GM_setValue('username', username);
                GM_setValue('password', password);
                alert('用户名和密码已保存！');
            } else {
                alert('请输入用户名和密码！');
            }
        });
    }
    window.addEventListener('load', function() {
        // 获取当前页面URL
        const currentUrl = window.location.href;
        // 目标子字符串
        const targetSubstring = 'http://172.20.6.53/eportal/success';
        // 检查当前URL是否包含目标子字符串
        if (currentUrl.includes(targetSubstring)) {
            console.log('登录成功，页面将在3秒后关闭');
        }
    });

    // 打印读取到的用户名和密码以确认存储成功（仅用于调试，实际使用中应移除）
    //console.log('Username:', username);
    //console.log('Password:', password);
    if (true){
        if(window.location.href.includes('172.20.6.53/eportal/success'))
        {
            console.log('登录成功，页面将在3秒后关闭');

        }else if (window.location.href.includes('172.20.6.53/eportal/')) {
            window.addEventListener('load', function() {
                const agreeButton = document.querySelector('div[onclick="agree()"]');
                if (agreeButton) {
                    agreeButton.click();
                    console.log('同意按钮已被点击');
                } else {
                    console.log('未找到同意按钮');
                }
            });
        } else if (window.location.href.includes('rz.zjhu.edu.cn/cas/')) {
            window.addEventListener('load', function() {
                // 查找ID为username的输入框并修改其value属性
                const usernameInput = document.getElementById('username');
                const passwordInput = document.getElementById('ppassword');
                if (usernameInput && passwordInput) {
                    usernameInput.value = username;
                    passwordInput.value = password;
                    const loginButton = document.getElementById('dl');
                    if(loginButton){
                        GM_setValue('isloading', true);
                        loginButton.click();
                    }
                } else {
                }
            });
        }
    }


})();

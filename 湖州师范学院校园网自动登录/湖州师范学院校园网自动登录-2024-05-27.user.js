// ==UserScript==
// @name         湖州师范学院校园网自动登录
// @namespace    hzsf
// @version      2024-05-27
// @description  校园网自动登录
// @author       kun
// @match        http://172.20.6.53/eportal/*
// @match        https://rz.zjhu.edu.cn/cas/*
// @grant        GM_getValue
// @grant        GM_setValue
// @icon         https://www.zjhu.edu.cn/_upload/tpl/00/0b/11/template11/favicon.ico
// ==/UserScript==

(function() {
    'use strict';
    // 读取存储的用户名和密码，如果不存在则提示用户输入
    let username = GM_getValue('username', null);
    let password = GM_getValue('password', null);
    if (!username || !password) {
        username = prompt('请输入你的用户名:');
        password = prompt('请输入你的密码:');
        // 存储用户名和密码
        GM_setValue('username', username);
        GM_setValue('password', password);
    }
    window.addEventListener('load', function() {
        // 获取当前页面URL
        const currentUrl = window.location.href;
        // 目标子字符串
        const targetSubstring = 'http://172.20.6.53/eportal/success';
        // 检查当前URL是否包含目标子字符串
        if (currentUrl.includes(targetSubstring)) {
            alert('登录成功');
            console.log('登录成功，页面将在3秒后关闭');
        }
    });
    // 打印读取到的用户名和密码以确认存储成功（仅用于调试，实际使用中应移除）
    //console.log('Username:', username);
    //console.log('Password:', password);
    if (username && password){
        if (window.location.href.includes('172.20.6.53/eportal/')) {
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

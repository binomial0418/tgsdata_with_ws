-- phpMyAdmin SQL Dump
-- version 4.9.6
-- https://www.phpmyadmin.net/
--
-- 主機： localhost
-- 產生時間： 2021 年 07 月 14 日 13:10
-- 伺服器版本： 10.3.24-MariaDB
-- PHP 版本： 7.3.24

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- 資料庫： `duckegg`
--

-- --------------------------------------------------------

--
-- 資料表結構 `tgsdata`
--

CREATE TABLE `tgsdata` (
  `log_no` bigint(20) UNSIGNED NOT NULL,
  `dev_typ` varchar(50) NOT NULL,
  `val` decimal(10,0) NOT NULL,
  `log_tim` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- 已傾印資料表的索引
--

--
-- 資料表索引 `tgsdata`
--
ALTER TABLE `tgsdata`
  ADD PRIMARY KEY (`log_no`),
  ADD UNIQUE KEY `log_no` (`log_no`),
  ADD KEY `envlog_index1` (`dev_typ`,`log_tim`),
  ADD KEY `log_no_2` (`log_no`),
  ADD KEY `log_no_3` (`log_no`);

--
-- 在傾印的資料表使用自動遞增(AUTO_INCREMENT)
--

--
-- 使用資料表自動遞增(AUTO_INCREMENT) `tgsdata`
--
ALTER TABLE `tgsdata`
  MODIFY `log_no` bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

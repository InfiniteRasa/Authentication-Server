-- phpMyAdmin SQL Dump
-- version 3.3.0
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: May 01, 2011 at 06:24 PM
-- Server version: 5.1.44
-- PHP Version: 5.2.13

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `test`
--

-- --------------------------------------------------------

--
-- Table structure for table `game_servers`
--

CREATE TABLE IF NOT EXISTS `game_servers` (
  `server_id` int(11) NOT NULL,
  `host` int(11) NOT NULL,
  `port` int(11) NOT NULL,
  `age_limit` int(11) NOT NULL,
  `pk_flag` int(11) NOT NULL,
  `current_users` int(11) NOT NULL,
  `max_users` int(11) NOT NULL,
  `status` int(11) NOT NULL,
  `check_time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `static` int(11) NOT NULL,
  PRIMARY KEY (`host`,`port`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `game_servers`
--

INSERT INTO `game_servers` (`server_id`, `host`, `port`, `age_limit`, `pk_flag`, `current_users`, `max_users`, `status`, `check_time`, `static`) VALUES
(53, 16777343, 8001, 18, 1, 1, 100, 1, '2011-05-01 18:04:50', 1);

-- --------------------------------------------------------

--
-- Table structure for table `sessions`
--

CREATE TABLE IF NOT EXISTS `sessions` (
  `session_id1` bigint(20) NOT NULL,
  `session_id2` bigint(20) NOT NULL,
  `uid` bigint(20) NOT NULL,
  `account` varchar(30) NOT NULL,
  `checktime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `sessions`
--

INSERT INTO `sessions` (`session_id1`, `session_id2`, `uid`, `account`, `checktime`) VALUES
(3340575638, 2318843403, 1, 'manolo', '2011-05-01 14:06:35');

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE IF NOT EXISTS `users` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `birthday` date NOT NULL,
  `blocked` tinyint(1) NOT NULL,
  `logged_in` tinyint(4) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`id`, `username`, `password`, `birthday`, `blocked`, `logged_in`) VALUES
(1, 'manolo', '12cdb9b24211557ef1802bf5a875fd2c', '0000-00-00', 0, 0);

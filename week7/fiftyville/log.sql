-- Keep a log of any SQL queries you execute as you solve the mystery.
-- First look at each table and get to know the meaning of each table
.schema
SELECT * FROM crime_scene_reports LIMIT 5;
-- crime_scene_reports recored the detail of this crime
-- select the target crime happend in July 28, 2021 on Humphrey Street
SELECT * FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street";
-- information got: 1) time 10:15am 2) at Humphrey Street bakery 3) three witnesses 4) intervew transcripts all contain "bakery" 5) case id: 295

-- next step is to find witnesses' interview by transcript contain "bakery" at that date
SELECT * FROM interviews WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE "%bakery%";
-- information got: | 161 | Ruth    | 2021 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
-- | 162 | Eugene  | 2021 | 7     | 28  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
-- | 163 | Raymond | 2021 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |

-- next step is to find more evidence by look at thief left within 10 min
-- before Eugene entered Emma's bakery, ATM on Leggett Street, thief withdraw mone
-- when thief leaving call someone in a minute, that person purchase flight ticket

-- suspicous license plates
SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute <=30 OR minute > 15;
-- find suspicous transactions people during that time
SELECT * FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";
-- find people who own those suspicous accounts
SELECT person_id FROM bank_accounts
WHERE account_number in (
    SELECT account_number FROM atm_transactions
    WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw"
);
-- find these person's plate liciense and get suspicious list
SELECT * FROM people
WHERE id in(
    SELECT person_id FROM bank_accounts
    WHERE account_number in (
        SELECT account_number FROM atm_transactions
        WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw")
) AND id in (
    SELECT id FROM people
    WHERE license_plate in (
        SELECT license_plate FROM bakery_security_logs
        WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute <=30 OR minute > 15
    )
);

-- according to phone number that duration < 60 and in suspicious list
CREATE TABLE suspicious_person AS
SELECT * FROM people
WHERE phone_number in (
    SELECT phone_number from people
    WHERE id in (
        SELECT person_id FROM bank_accounts
        WHERE account_number in (
            SELECT account_number FROM atm_transactions
            WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw"
        )
    )
) AND phone_number in (
    SELECT phone_number from people
    WHERE id in (
        SELECT id FROM people
        WHERE license_plate in (
            SELECT license_plate FROM bakery_security_logs
            WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute <=30 OR minute > 15
        )
    )
) AND phone_number in (
    SELECT phone_number from people
    WHERE phone_number in (
        SELECT caller FROM phone_calls
        WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60
    )
);

-- next step is to check people who book ticket only airport CSF in city Fiftyville
SELECT * FROM airports WHERE city = "Fiftyville";
-- find flights departure from CSF in 07/29/2021 and ordered by time
SELECT * FROM flights
WHERE origin_airport_id = 8 AND year = 2021 AND month = 7 AND day = 29
ORDER BY hour ASC;
-- the ealist filight is 36
SELECT * FROM passengers WHERE flight_id = 36;
-- find the possible receiver
CREATE TABLE suspicious_accomplice AS
SELECT * FROM people
WHERE phone_number in (
    SELECT receiver FROM phone_calls
    WHERE caller in (
        SELECT phone_number FROM suspicious_person
    ) AND year = 2021 AND month = 7 AND day = 28 AND duration < 60
);
-- find the thief
SELECT *
FROM suspicious_person sp

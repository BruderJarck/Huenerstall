now_month = 4
old_month = None

uptime_h = 10
uptime_m = 0

downtime_h = 15
downtime_m = 0

for now_month in range(12):
    now_month += 1
    if now_month != old_month:
        if now_month <= 12 and now_month >= 7:
            uptime_h += 0.8
            downtime_h -= 1.2

        else:
            uptime_h -= 0.8
            downtime_h += 1.2

        old_month = now_month

    print(now_month, f"{int(uptime_h)}:{uptime_m}/{int(downtime_h)}:{downtime_m}")

# problem statement: https://csacademy.com/ieeextreme-practice/task/disparate-datasets

import csv
import sys


def parse_input():
    events = []
    reader = csv.reader(sys.stdin)
    for row in reader:
        event_id, title, acronym, project_code, project_3_digit_code, record_type = row
        if acronym == '':
            continue
        events.append({
            'Event ID': event_id,
            'Event Title': title,
            'Acronym': acronym,
            'Project Code': project_code,
            '3 Digit Project Code': project_3_digit_code,
            'Record Type': record_type
        })
    return events


def is_parent_event(rec):
    return rec['Record Type'] == 'Parent Event'


def organize_events(events):
    record = {}
    res = {}
    for event in events:
        if event['Acronym'] not in record:
            record[event['Acronym']] = []
        record[event['Acronym']].append(event)
    for key, value in record.items():
        value.sort(key=lambda rec: (
            not is_parent_event(rec),
            rec['Event Title'],
            rec['Event ID']
        ))
        if not is_parent_event(value[0]):
            continue
        elif len(value) == 1:
            continue
        elif is_parent_event(value[1]):
            continue
        else:
            child_codes = set([child['3 Digit Project Code'] for child in value[1:]])
            if len(child_codes) == 1:
                value[0]['3 Digit Project Code'] = child_codes.pop()
            else:
                value[0]['3 Digit Project Code'] = '???'
            res[key] = value
    return res


def csv_escape(text):
    return '"{}"'.format(text.replace('"', '""'))


def output_results(valid_sets):
    for acronym in sorted(valid_sets.keys()):
        parent = valid_sets[acronym][0]
        children = valid_sets[acronym][1:]

        print("{},{},{},{},{},{}".format(
            parent['Event ID'],
            csv_escape(parent['Event Title']),
            csv_escape(parent['Acronym']),
            parent['Project Code'],
            parent['3 Digit Project Code'],
            csv_escape(parent['Record Type'])
        ))

        for child in children:
            print("{},{},{},{},{},{},{}".format(
                child['Event ID'],
                csv_escape(child['Event Title']),
                csv_escape(child['Acronym']),
                child['Project Code'],
                child['3 Digit Project Code'],
                csv_escape(child['Record Type']),
                parent['Event ID']
            ))


if __name__ == '__main__':
    output_results(organize_events(parse_input()))
